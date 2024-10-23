/*$(document).ready(function() {
    $('#miBoton').on('mousedown', function() {
        console.log("Hola");
    });

    $('#miBoton').on('mouseup', function() {
        console.log("Mundo!");
    });
});//mousedown click, mouse up leave*/

/*setInterval(function () {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("temperature").innerHTML = this.responseText;
        }
    };
    xhttp.open("GET", "/temperature", true);
    xhttp.send();
}, 3000);

setInterval(function () {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("humidity").innerHTML = this.responseText;
        }
    };
    xhttp.open("GET", "/humidity", true);
    xhttp.send();
}, 3000);*/

function login(password) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            if (this.responseText != null && this.responseText != "") {
                document.getElementById('logged').removeAttribute("hidden", "");
                setCookie("webAccessUUID", this.responseText, 1);
            } else {
                checkAuth(true);
            }
        }
    };
    xhttp.open("GET", `/auth?password=${password}`, true);
    xhttp.send();
}

function updateAllStates() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            if (this.responseText == "notLogged") {
                document.getElementById('logged').setAttribute("hidden", "");
            } else {
                var arr = JSON.parse(this.responseText);
                for (var i = 0; i < arr.length; i++) {
                    document.getElementById(`d${i}state`).innerHTML = arr[i];
                }
            }
        }
    };
    xhttp.open("GET", `/updateStates?uuid=${getCookie("webAccessUUID")}`, true);
    xhttp.send();
}

function checkAuth(sendAlert) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            if (this.responseText == "true") {
                document.getElementById('logged').removeAttribute("hidden");
                updateAllStates();
            } else {
                document.getElementById('logged').setAttribute("hidden", "");
                if (sendAlert) {
                    login(prompt("Enter your password", ""));
                }
            }
        }
    };
    xhttp.open("GET", `/checkAuth?uuid=${getCookie("webAccessUUID")}`, true);
    xhttp.send();
}

function OnButtonClick(call, pin) {
    console.log("Pin: " + pin + "\nNew state: " + call);
    /*let xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            if (this.responseText == "") {
                checkAuth();
            } else {
                document.getElementById(`d${pin}state`).innerHTML = this.responseText;
            }
        }
    };
    xhttp.open("GET", `/${call}?pin=${pin}&uuid=${getCookie("webAccessUUID")}`);
    xhttp.send();*/
}