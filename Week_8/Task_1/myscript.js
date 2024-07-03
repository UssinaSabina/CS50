
// run script once DOM is loaded
document.addEventListener("DOMContentLoaded", function() {
    // if the answer is correct change button collor to green
    // get all elements with class "correct"
    let correct = document.querySelector(".correct");
    // Add event listeners to each correct button
    correct.addEventListener("click", function() {
        // Set background color to green
        correct.style.backgroundColor = "green";
        document.querySelector("#feedback1").innerHTML = "Correct!";
    });

    // when any incorrect answer is clicked, change button color to red
    let incorrects = document.querySelectorAll(".incorrect");
    for (let i = 0; i < incorrects.length;  i++0) {
        incorrects[i].addEventListener("click", function() {
            // Set background color to red
            incorrects[i].style.backgroundColor = "red";
            document.querySelector("#feedback1").innerHTML = "Incorrect";
        });
    }

    // check free response answer
    document.querySelector('#check').addEventListener('click', function() {
        let input = document.querySelector('#check');
        if (input.value == 'strip()') {
            input.style.backgroundColor = 'green';
            document.querySelector('#feedback2').innerHTML = 'Correct!';
        }
        else {
            input.style.backgroundColor = 'red';
            document.querySelector('#feedback2').innerHTML = 'Incorrect';
        }
    });
});
