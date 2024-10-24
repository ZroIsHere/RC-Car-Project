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

$(document).ready(function() {
    $('#up').on('mousedown touchstart', function() { SetPinState('0', 'high'); });
    $('#up').on('mouseup touchend', function() { SetPinState('0', 'low'); });
  
    $('#down').on('mousedown touchstart', function() { SetPinState('1', 'high'); });
    $('#down').on('mouseup touchend', function() { SetPinState('1', 'low'); });
  
    $('#left').on('mousedown touchstart', function() { SetPinState('2', 'high'); });
    $('#left').on('mouseup touchend', function() { SetPinState('2', 'low'); });
  
    $('#right').on('mousedown touchstart', function() { SetPinState('3', 'high'); });
    $('#right').on('mouseup touchend', function() { SetPinState('3', 'low'); });
  
    $('#headlights').on('click', function() { ChangePinState('4'); });
    $('#rearlights').on('click', function() { ChangePinState('5'); });
  });