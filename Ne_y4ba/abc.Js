let slider = document.getElementById("myRange"), timer_ball, ball_x = 850, ball_y = 650, speed_x_ball = 4, speed_y_ball = 2, timer_model, model_y = ball_y, model_x = ball_x,
  speed = document.getElementById("speed"), radius = 15, s = 0, timer_ms, ms = 0, min = 0, flag_stop = false, flag_play = false,
  speed_x_model = speed_x_ball, speed_y_model = speed_y_ball;

function polsunok() {
  //sad.innerHTML = slider.value;
  draw(slider.value - "0");
  drawballstop();
  ball_x = 850, ball_y = 650, speed_x_ball = 4, speed_y_ball = 2, model_y = ball_y,
    model_x = ball_x, speed_x_model = speed_x_ball, speed_y_model = speed_y_ball;
  model();
  ball();
  obj();
  mod();
  flag_stop = false, flag_play = false;
}

function obj() {
  const canvas = document.getElementById("obj");
  if (canvas.getContext) {
    const ctx = canvas.getContext("2d");
    ctx.beginPath();
    ctx.canvas.width = 50;
    ctx.canvas.height = 50;
    ctx.arc(25, 25, radius, 0, Math.PI * 2);
    ctx.fillStyle = "red";
    ctx.fill();
    ctx.closePath();
  }
}

function mod() {
  const canvas = document.getElementById("mod");
  if (canvas.getContext) {
    const ctx = canvas.getContext("2d");
    ctx.beginPath();
    ctx.canvas.width = 50;
    ctx.canvas.height = 50;
    ctx.lineWidth = 4;
    ctx.arc(25, 25, radius + 2, 0, Math.PI * 2);
    ctx.strokeStyle = "green";
    ctx.stroke();
    ctx.closePath();
  }
}

function check_pos() {
  if (ball_x > model_x + radius * 2 || ball_x + radius * 2 < model_x || ball_y > model_y + radius * 2 || ball_y + radius * 2 < model_y) {
    drawballstop();
  }
}

function model() {
  const canvas = document.getElementById("model");
  if (canvas.getContext) {
    const ctx = canvas.getContext("2d");
    ctx.beginPath();
    ctx.canvas.width = 1800;
    ctx.canvas.height = 1550;
    ctx.lineWidth = 4;
    ctx.arc(model_x, model_y, radius + 2, 0, Math.PI * 2);
    ctx.strokeStyle = "green";
    check_model();
    model_x += speed_x_model;
    model_y += speed_y_model;
    ctx.stroke();
    ctx.closePath();
    check_pos();
  }
}

function ball() {
  const canvas = document.getElementById("ball");
  if (canvas.getContext) {
    const ctx = canvas.getContext("2d");
    ctx.beginPath();
    ctx.canvas.width = 1800;
    ctx.canvas.height = 1550;
    ctx.arc(ball_x, ball_y, radius, 0, Math.PI * 2);
    ctx.fillStyle = "red";
    check_ball();
    ball_x += speed_x_ball;
    ball_y += speed_y_ball;
    ctx.fill();
    ctx.closePath();
    check_pos();
  }
}

function height() {
  text_ms.innerHTML = ms;
  text_s.innerHTML = s;
  text_min.innerHTML = min;
  ms++;
  if (ms > 250) {
    ms = 0;
    s++;
  }
  if (s > 59) {
    s = 0;
    min++;
  }
}

function Timer() {
  Timerstop();
  s = 0;
  ms = 0;
  min = 0;
  timer_ms = setInterval(height, 1);
}

function Timergo() {
  Timerstop();
  timer_ms = setInterval(height, 1);
}

function Timerstop() {
  clearInterval(timer_ms);
}

function drawball() {
  ball_x = 850, ball_y = 650;
  model_x = ball_x, model_y = ball_y;
  drawballstop();
  polsunok();
  Timer();
  timer_ball = setInterval(ball, speed.value);
  timer_model = setInterval(model, speed.value);
  flag_play = true;
}

function dwarballgo() {
  if (flag_stop) {
    drawballstop();
    Timergo();
    timer_ball = setInterval(ball, speed.value);
    timer_model = setInterval(model, speed.value);
    flag_stop = false;
    flag_play = true;
  }
}

function drawballstop() {
  if (flag_play) {
    clearInterval(timer_model);
    clearInterval(timer_ball);
    Timerstop();
    flag_stop = true;
    flag_play = false;
  }
}

let x = [[], [], [], []];
let y = [[], [], [], []];

function draw(a) {
  const canvas = document.getElementById("pole");
  if (canvas.getContext) {
    const ctx = canvas.getContext("2d");
    //ctx.canvas.width = window.innerWidth;
    //ctx.canvas.height = window.innerHeight;
    ctx.canvas.width = 1800;
    ctx.canvas.height = 1550;
    let start_x = [380, 1380];
    let start_y = [380, 1130];
    ctx.beginPath();
    ctx.moveTo(start_x[0], start_y[0]);
    ctx.quadraticCurveTo((start_x[1] + start_x[0]) / 2, start_y[0] - a, start_x[1], start_y[0]);
    ctx.quadraticCurveTo(start_x[1] + a, (start_y[1] + start_y[0]) / 2, start_x[1], start_y[1]);
    ctx.quadraticCurveTo((start_x[1] + start_x[0]) / 2, start_y[1] + a, start_x[0], start_y[1]);
    ctx.quadraticCurveTo(start_x[0] - a, (start_y[1] + start_y[0]) / 2, start_x[0], start_y[0]);
    ctx.stroke();

    x[0][0] = start_x[0];
    x[0][1] = (start_x[1] + start_x[0]) / 2;
    x[0][2] = start_x[1];

    x[1][0] = start_x[1];
    x[1][1] = start_x[1] + a;
    x[1][2] = start_x[1];

    x[2][0] = start_x[1];
    x[2][1] = (start_x[1] + start_x[0]) / 2;
    x[2][2] = start_x[0];

    x[3][0] = start_x[0];
    x[3][1] = start_x[0] - a;
    x[3][2] = start_x[0];

    y[0][0] = start_y[0];
    y[0][1] = start_y[0] - a;
    y[0][2] = start_y[0];

    y[1][0] = start_y[0];
    y[1][1] = (start_y[1] + start_y[0]) / 2;
    y[1][2] = start_y[1];

    y[2][0] = start_y[1];
    y[2][1] = start_y[1] + a;
    y[2][2] = start_y[1];

    y[3][0] = start_y[1];
    y[3][1] = (start_y[1] + start_y[0]) / 2;
    y[3][2] = start_y[0];
  }
}

function check_ball() {
  let flag = false, flag1 = false;
  for (b = 0; b < 4; ++b) {
    flag = false;
    for (t = 0; t <= 1; t += 0.05) {
      let x1 = Math.pow((1 - t), 2) * x[b][0] + 2 * (1 - t) * t * x[b][1] + Math.pow(t, 2) * x[b][2];
      let y1 = Math.pow((1 - t), 2) * y[b][0] + 2 * (1 - t) * t * y[b][1] + Math.pow(t, 2) * y[b][2];
      switch (b) {
        case 0:
          if (ball_y < y1 + radius) {
            speed_y_ball *= -1;
            flag = true;
          }
          break;
        case 1:
          if (ball_x > x1 - radius) {
            speed_x_ball *= -1;
            flag = true;
          }
          break;
        case 2:
          if (ball_y > y1 - radius) {
            speed_y_ball *= -1;
            flag = true;
          }
          break;
        case 3:
          if (ball_x < x1 + radius) {
            speed_x_ball *= -1;
            flag = true;
          }
          break;
      }
      if (flag) {
        flag1 = true;
        break;
      }
    }
    if (flag1) {
      break;
    }
  }
}

function check_model() {
  let flag = false, flag1 = false;
  for (b = 0; b < 4; ++b) {
    flag = false;
    for (t = 0; t <= 1; t += 0.05) {
      let x1 = Math.pow((1 - t), 2) * x[b][0] + 2 * (1 - t) * t * x[b][1] + Math.pow(t, 2) * x[b][2];
      let y1 = Math.pow((1 - t), 2) * y[b][0] + 2 * (1 - t) * t * y[b][1] + Math.pow(t, 2) * y[b][2];
      switch (b) {
        case 0:
          if (model_y < y1 + radius + 2) {
            speed_y_model *= -1;
            flag = true;
          }
          break;
        case 1:
          if (model_x > x1 - (radius + 2)) {
            speed_x_model *= -1;
            flag = true;
          }
          break;
        case 2:
          if (model_y > y1 - (radius + 2)) {
            speed_y_model *= -1;
            flag = true;
          }
          break;
        case 3:
          if (model_x < x1 + radius + 2) {
            speed_x_model *= -1;
            flag = true;
          }
          break;
      }
      if (flag) {
        flag1 = true;
        break;
      }
    }
    if (flag1) {
      break;
    }
  }
}

polsunok();