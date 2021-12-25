import {ButtonView} from "./ButtonView";

class ToolbarView {
    private m_createRectangleButton: ButtonView
    private m_createEllipseButton: ButtonView
    private m_createTriangleButton: ButtonView
    private m_saveDocumentButton: ButtonView
    private m_deleteButton: ButtonView
    private m_uploadDocumentButton: ButtonView
    private readonly m_toolbarHtml: HTMLElement

    constructor(createRectFn: () => void, createTriangleFn: () => void, createEllipseFn: () => void, deleteFn: () => void, saveFn: () => void, uploadFn: () => void, parentElement: HTMLElement) {
        this.m_toolbarHtml = document.createElement('div')
        this.m_createRectangleButton = new ButtonView('Rectangle', 'button')
        this.m_createRectangleButton.getOnClickSignal().add(() => createRectFn())
        this.m_createEllipseButton = new ButtonView('Ellipse', 'button')
        this.m_createEllipseButton.getOnClickSignal().add(() => createEllipseFn())
        this.m_createTriangleButton = new ButtonView('Triangle', 'button')
        this.m_createTriangleButton.getOnClickSignal().add(() => createTriangleFn())
        this.m_deleteButton = new ButtonView('Delete', 'button')
        this.m_deleteButton.getOnClickSignal().add(() => deleteFn())
        this.m_saveDocumentButton = new ButtonView('Save', 'button')
        this.m_saveDocumentButton.getOnClickSignal().add(() => saveFn())
        this.m_uploadDocumentButton = new ButtonView('Upload', 'button')
        this.m_uploadDocumentButton.getOnClickSignal().add(() => uploadFn())
        this.render(parentElement)
    }

    private render(parentElement: HTMLElement) {
        this.m_toolbarHtml.classList.add('toolbar')
        parentElement.appendChild(this.m_toolbarHtml)
        this.m_createRectangleButton.render(this.m_toolbarHtml)
        this.m_createEllipseButton.render(this.m_toolbarHtml)
        this.m_createTriangleButton.render(this.m_toolbarHtml)
        this.m_saveDocumentButton.render(this.m_toolbarHtml)
        this.m_deleteButton.render(this.m_toolbarHtml)
        this.m_uploadDocumentButton.render(this.m_toolbarHtml)
    }
}

export {
    ToolbarView
}