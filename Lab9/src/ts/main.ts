import {EditorView} from "./View/EditorView";

function startApp() {
    const editorRenderer = new EditorView()
    editorRenderer.render()
}

window.onload = () => {
    startApp()
}