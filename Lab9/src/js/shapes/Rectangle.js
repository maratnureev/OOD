"use strict";
var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (Object.prototype.hasOwnProperty.call(b, p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        if (typeof b !== "function" && b !== null)
            throw new TypeError("Class extends value " + String(b) + " is not a constructor or null");
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
exports.RectangleRenderer = void 0;
var ShapeRenderer_1 = require("./ShapeRenderer");
var RectangleRenderer = /** @class */ (function (_super) {
    __extends(RectangleRenderer, _super);
    function RectangleRenderer(model, canvas) {
        return _super.call(this, model, canvas) || this;
    }
    RectangleRenderer.prototype.getShapeHtmlImpl = function () {
        var model = this.getModel();
        var width = model.width;
        var height = model.height;
        return "<svg\n            xmlns='http://www.w3.org/2000/svg'\n            width='" + width + "'\n            height='" + height + "'\n            viewPort='0 0 " + width + " " + height + "'>\"\n            <polygon points='" + 0 + "," + 0 + " " + width + "," + 0 + " " + width + "," + height + " " + 0 + "," + height + "' fill='black' />\n        </svg>";
    };
    return RectangleRenderer;
}(ShapeRenderer_1.ShapeRenderer));
exports.RectangleRenderer = RectangleRenderer;
//# sourceMappingURL=Rectangle.js.map