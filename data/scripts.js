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

function SetEngineSpeed(pin, speed) {
    console.log("Pin: " + pin + "\nSpeed: " + speed);
    let xhttp = new XMLHttpRequest();
    xhttp.open("POST", `/setEngineSpeed?pin=${pin}&speed=${speed}`);
    xhttp.send();
}

$(document).ready(function() {
    SetEngineSpeed('0', '0');
    SetPinState('1', 'low');
    SetPinState('2', 'low');
    SetPinState('3', 'low');
    SetPinState('4', 'low');
    SetPinState('5', 'low');
    
    $('#up').on('mousedown touchstart', function() { SetEngineSpeed('0', '255'); });//Change this high with the slide value
    $('#up').on('mouseup touchend', function() { SetEngineSpeed('0', '0'); });
  
    $('#down').on('mousedown touchstart', function() { SetPinState('1', 'high'); });
    $('#down').on('mouseup touchend', function() { SetPinState('1', 'low'); });
  
    $('#left').on('mousedown touchstart', function() { SetPinState('2', 'high'); });
    $('#left').on('mouseup touchend', function() { SetPinState('2', 'low'); });
  
    $('#right').on('mousedown touchstart', function() { SetPinState('3', 'high'); });
    $('#right').on('mouseup touchend', function() { SetPinState('3', 'low'); });
  
    $('#headlights').on('click', function() { ChangePinState('4'); });
    $('#rearlights').on('click', function() { ChangePinState('5'); });
});