import { Canvas } from "./Model/Canvas";
import { Frame } from "./Model/Frame";
import { Shape } from "./Model/Shape";
import { ShapeType } from "./Model/ShapeType";

abstract class Serializer {
    abstract serializeCanvas(canvas: Canvas): string
}

class JsonSerializer implements Serializer {
    serializeCanvas(canvas: Canvas) {
        return JSON.stringify({
            width: canvas.getWidth(),
            height: canvas.getHeight(),
            shapes: canvas.getShapes().map(shape => JsonSerializer.seriailzeShape(shape)),
        })
    }

    private static seriailzeShape(shape: Shape) {
        return {
            id: shape.getId(),
            frame: shape.getFrame(),
            type: shape.getType(),
        }
    }
}

type SerializedCanvas = {
    width: number
    height: number
    shapes: SerializedShape[]
}

type SerializedShape = {
    id: string,
    frame: Frame
    type: ShapeType
}

export {
    Serializer,
    JsonSerializer
}

export type {
    SerializedCanvas,
    SerializedShape,
}