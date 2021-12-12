import {Editor} from "./Model/Editor";
import {EditorView} from "./View/EditorView";

function startApp() {
    const editor = new Editor(640, 480)
    const parentElement = document.getElementById("editor") as HTMLElement
    const editorRenderer = new EditorView(editor, parentElement)
    editorRenderer.render()
}

window.onload = () => {
    startApp()
}