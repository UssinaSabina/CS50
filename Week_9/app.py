import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, local_time

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    portfolio = db.execute("SELECT * FROM portfolios WHERE user_id = ? ORDER BY invested", user_id)
    cash_left = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    portfolio_value = 0
    total_delta = 0

    # Update info (the current price and the overall stock value) for each stock to be displayed in real time
    try:
        for stock in portfolio:
            symbol = stock["symbol"]

            stock_info = lookup(symbol)

            current_price = stock_info["price"]
            total_current_price = current_price * stock["shares"]
            invested = stock["invested"]
            current_profit = total_current_price - invested

            stock.update({"current_price": current_price,
                         "total_current_price": total_current_price, "delta": current_profit})

            portfolio_value += total_current_price
            total_delta += current_profit

    except (ValueError, LookupError):
        return apology("failed to update stock prices")

    return render_template("index.html", portfolio=portfolio, cash_left=cash_left, portfolio_value=portfolio_value, total_delta=total_delta)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol")

        # Ensure that the input isn't blank
        if not symbol:
            return apology("symbol can't be blank")

        # Search for stock's info
        stock = lookup(symbol)

        # Ensure that search's result isn't empty (aka symbol exists)
        if stock == None:
            return apology("symbol doesn't exist")

        # Get the number of shares
        shares = request.form.get("shares")

        # Ensure input isn't blank and is indeed a number
        if shares == "" or not shares.isdigit():
            return apology("shares are missing")

        shares = int(shares)

        # Ensure that the number of shares is a positive integer
        if shares <= 0:
            return apology("number of shares can't be zero or less than zero")

        total_cost = shares * stock["price"]

        # Ensure user has enough cash
        user_id = session["user_id"]
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?;", user_id)
        user_cash = user_cash[0]["cash"]

        if total_cost > user_cash:
            return apology("not enough money")

        # Perform the aquisition and update database
        update_user_cash = user_cash - total_cost
        db.execute("UPDATE users SET cash = ? WHERE id = ?;", update_user_cash, user_id)

        # Add transaction to transactions table
        db.execute("""
            INSERT INTO transactions (user_id, date_time, symbol, shares, price, action)
            VALUES (?, ?, ?, ?, ?, ?);
            """,
                   user_id,
                   local_time(),
                   stock["symbol"],
                   shares,
                   stock["price"],
                   "buy"
                   )

        # Update portfolios table
        try:
            # if there is no shares of this particular stock in portfolio
            db.execute("""
                INSERT INTO portfolios (user_id, symbol, shares, current_price, total_current_price, invested, delta)
                VALUES (?, ?, ?, ?, ?, ?, ?);
                """,
                       user_id,
                       stock["symbol"],
                       shares,
                       stock["price"],
                       shares * stock["price"],
                       shares * stock["price"],
                       0
                       )
        except:
            # if the user already has shares of this particular stock
            owned_shares = db.execute("SELECT shares FROM portfolios WHERE user_id = ? AND symbol = ?;",
                                      user_id,
                                      stock["symbol"])
            owned_shares = owned_shares[0]["shares"]

            already_invested = db.execute("SELECT invested FROM portfolios WHERE user_id = ? AND symbol = ?;",
                                          user_id,
                                          stock["symbol"])
            already_invested = already_invested[0]["invested"]

            db.execute("""
                UPDATE portfolios
                SET shares = ?,
                    current_price = ?,
                    total_current_price = ?,
                    invested = ?,
                    delta = ?
                WHERE user_id = ? AND symbol = ?;
                """,
                       owned_shares + shares,
                       stock["price"],
                       (owned_shares + shares) * stock["price"],
                       already_invested + total_cost,
                       round((owned_shares + shares) * stock["price"] -
                             (already_invested + total_cost), 2),
                       user_id,
                       stock["symbol"]
                       )

        # Inform user about succesfull payment
        flash(f"Successfully bought {shares} shares of {symbol}!")

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?;", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        symbol = request.form.get("symbol")

        # Ensure symbol is not blank
        if not symbol:
            apology("symbol can't be blank")

        # search for stock's info
        stock = lookup(symbol)

        # Ensure symbol exists
        if stock == None:
            return apology("symbol doesn't exist")

        # Format price
        stock["price"] = usd(stock["price"])

        return render_template("quoted.html", stock=stock)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        if not password:
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        if not confirmation:
            return apology("must confirm your password", 400)

        # Ensure passwords match
        if password != confirmation:
            return apology("passwords don't match", 400)

        # Ensure username doesn't exist already and add the new user into database
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?);",
                       username, generate_password_hash(password))
        except:
            return apology("this username already exists, try a different one", 400)

        # Remember which user has logged in
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]

        return redirect("/")
    else:
        return (render_template("register.html"))


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = session["user_id"]
    portfolio = db.execute("SELECT * FROM portfolios WHERE user_id = ?", user_id)

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol")

        stock = lookup(symbol)

        # if the user fails to select a stock
        if not symbol:
            return apology("please, select a symbol")

        shares = int(request.form.get("shares"))

        shares_owned = db.execute(
            "SELECT shares FROM portfolios WHERE user_id = ? AND symbol = ?", user_id, symbol)[0]["shares"]

        # if the user doesn't own any shares of that stock
        if not shares_owned:
            return apology(f"you don't own any shares of {symbol}")

        # if the input is not a positive integer
        if shares <= 0:
            return apology("number of shares should be positive")

        # if the user doesn't own that many shares of the stock
        if shares > shares_owned:
            return apology(f"you don't own enough shares of {symbol}")

        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        current_price = stock["price"]
        cash_updated = cash + current_price * shares

        # Perform the sale
        if shares < shares_owned:
            # Update portfolios table if user sells less shares than the total amount he owns
            db.execute("UPDATE portfolios SET shares = ? WHERE user_id = ? AND symbol = ?",
                       shares_owned - shares, user_id, symbol)

        else:
            # Delete stock from portfolio if all shares were sold
            db.execute("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", user_id, symbol)

        # Update user's cash in database
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_updated, user_id)

        # Add transaction info to database
        db.execute("INSERT INTO transactions (user_id, date_time, symbol, shares, price, action) VALUES (?, ?, ?, ?, ?, ?)",
                   user_id,
                   local_time(),
                   symbol,
                   shares,
                   current_price,
                   "sell")

        # Inform user about succesfull deal
        flash(f"Successfully sold {shares} shares of {symbol}!")
        return redirect("/")
    else:
        # User reached route via GET (as by clicking a link or via redirect)
        return render_template("sell.html", portfolio=portfolio)


@app.route("/settings")
@login_required
def settings():
    """Show settings"""

    user_id = session["user_id"]
    username = db.execute("SELECT username FROM users WHERE id = ?", user_id)

    return render_template("settings.html", username=username[0]['username'])


@app.route("/changepassword", methods=["GET", "POST"])
@login_required
def changepassword():
    """Change password"""

    user_id = session["user_id"]

    if request.method == "POST":
        current_password = request.form.get("currentpassword")
        new_password = request.form.get("newpassword")
        confirmation = request.form.get("confirmation")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE id = ?", user_id)

        # Ensure password == confirmation
        if new_password != confirmation:
            return apology("the passwords do not match", 400)

        # Ensure inputs aren't blank
        if current_password == "" or new_password == "" or confirmation == "":
            return apology("inputs cannot be blank", 400)

        # Ensure current password is correct
        if not check_password_hash(rows[0]["hash"], current_password):
            return apology("invalid current password", 403)
        else:
            new_hash = generate_password_hash(new_password)
            db.execute("UPDATE users SET hash = ? WHERE id = ?", new_hash, user_id)

        # Redirect user to settings
        return redirect("/settings")

    else:
        return render_template("changepassword.html")


@app.route("/addcash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Add cash"""

    user_id = session["user_id"]

    if request.method == "POST":
        amount = int(request.form.get("amount"))
        password = request.form.get("password")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE id = ?", user_id)

        # Ensure password is correct
        if not check_password_hash(rows[0]["hash"], password):
            return apology("invalid current password", 403)
        else:
            # Add cash to account
            new_cash = rows[0]["cash"] + amount
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)
            # Add information about transaction to the database
            db.execute("INSERT INTO cash (user_id, date_time, amount, action) VALUES (?, ?, ?, ?)",
                       user_id,
                       local_time(),
                       amount,
                       "add")
            flash(f"Successfully added ${amount} to your balance!")
            return redirect("/")
    else:
        return render_template("addcash.html")


@app.route("/withdraw", methods=["GET", "POST"])
@login_required
def withdraw():
    """Withdraw cash from account"""

    user_id = session["user_id"]

    if request.method == "POST":
        # money to withdraw
        amount = int(request.form.get("amount"))
        # confirmation
        password = request.form.get("password")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE id = ?", user_id)

        # Ensure password is correct
        if not check_password_hash(rows[0]["hash"], password):
            return apology("invalid current password", 403)
        else:
            # Ensure there is enough cash to withdraw
            cash_current = rows[0]["cash"]
            if cash_current < amount:
                return apology("not enough cash", 403)

            # Withdraw cash from account
            new_cash = cash_current - amount
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)
            # Add information about transaction to the database
            db.execute("INSERT INTO cash (user_id, date_time, amount, action) VALUES (?, ?, ?, ?)",
                       user_id,
                       local_time(),
                       amount,
                       "withdraw")
            flash(f"Successfully withdrawed ${amount} from your balance!")
            return redirect("/")
    else:
        return render_template("withdraw.html")
