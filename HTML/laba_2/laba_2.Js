var i = 0;
var image = document.getElementById("image");
var images = new Array('images/ob1.png', 'images/ob2.png', 'images/ob3.png', 'images/ob4.png');

function img1() {
    if (i >= 3) {
        i = -1;
    }
    image.src = images[++i];
}

function img2() {
    if (i <= 0) {
        i = 4;
    }
    image.src = images[--i];
}

function img3(a) {
    i = a;
    image.src = images[i];
}