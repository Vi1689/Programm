var i = 0;
var image = document.getElementById("image");
var imges = new Array('images/ob1.png', 'images/ob2.png', 'images/ob3.png', 'images/ob4.png');

function img1() {
    if (i >= 3) {
        i = -1;
    }
    image.src = imges[++i];
}

function img2() {
    if (i <= 0) {
        i = 4;
    }
    image.src = imges[--i];
}

function img3(i) {
    image.src = imges[i];
}