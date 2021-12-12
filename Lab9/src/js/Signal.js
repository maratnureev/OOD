"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Signal = exports.ISignal = void 0;
var ISignal = /** @class */ (function () {
    function ISignal() {
    }
    return ISignal;
}());
exports.ISignal = ISignal;
var Signal = /** @class */ (function () {
    function Signal() {
        this.m_listeners = [];
    }
    Signal.prototype.add = function (fn) {
        var _this = this;
        this.m_listeners.push(fn);
        return function () {
            var index = _this.m_listeners.indexOf(fn);
            if (index >= 0) {
                _this.m_listeners.splice(index, 1);
            }
        };
    };
    Signal.prototype.addCallOnce = function (fn) {
        var unsub = this.add(function (value) {
            fn(value);
            unsub();
        });
    };
    Signal.prototype.dispatch = function (value) {
        for (var _i = 0, _a = this.m_listeners; _i < _a.length; _i++) {
            var sb = _a[_i];
            sb(value);
        }
    };
    return Signal;
}());
exports.Signal = Signal;
//# sourceMappingURL=Signal.js.map