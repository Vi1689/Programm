var i = 1;
var image = document.getElementById("image");
var imges = new Array('images/ob1.png', 'images/ob2.png', 'images/ob3.png', 'images/ob4.png');
function imgsrc() {
    image.src = imges[i++];
    if (i >= 4) {
        i = 0;
    }
}