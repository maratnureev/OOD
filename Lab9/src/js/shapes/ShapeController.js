"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.ShapeController = void 0;
var ShapeController = /** @class */ (function () {
    function ShapeController(model, view) {
        this.m_model = model;
        this.m_view = view;
    }
    ShapeController.prototype.setPosition = function (left, top) {
        this.m_model.setPosition(left, top);
    };
    ShapeController.prototype.setSize = function (width, height) {
        this.m_model.setSize(width, height);
    };
    return ShapeController;
}());
exports.ShapeController = ShapeController;
//# sourceMappingURL=ShapeController.js.map