/*$(document).ready(function() {
    $('#miBoton').on('mousedown', function() {
        console.log("Hola");
    });

    $('#miBoton').on('mouseup', function() {
        console.log("Mundo!");
    });
});//mousedown click, mouse up leave*/


function SetPinState(pin, state) {
    console.log("Pin: " + pin + "\nNew state: " + state);
    let xhttp = new XMLHttpRequest();
    xhttp.open("POST", `/setPinState?pin=${pin}&state=${state}`);
    xhttp.send();
}

function ChangePinState(pin) {
    console.log("Pin: " + pin);
    let xhttp = new XMLHttpRequest();
    xhttp.open("POST", `/changePinState?pin=${pin}`);
    xhttp.send();
}