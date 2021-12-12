"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var Rectangle_1 = require("./shapes/Rectangle");
var Shape_1 = require("./shapes/Shape");
var Triangle_1 = require("./shapes/Triangle");
function startApp() {
    var rect = new Shape_1.Shape(200, 100, 50, 50);
    var triangle = new Shape_1.Shape(100, 100, 200, 50);
    var canvas = document.getElementById("editor");
    var renderer = new Rectangle_1.RectangleRenderer(rect, canvas);
    var rendererTriangle = new Triangle_1.TriangleRenderer(triangle, canvas);
    renderer.render();
    rendererTriangle.render();
}
window.onload = function () {
    startApp();
};
//# sourceMappingURL=main.js.map