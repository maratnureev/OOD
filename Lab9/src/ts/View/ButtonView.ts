import {IEvent, Event} from "../Event";

class ButtonView {
    private buttonHTML = document.createElement('button')
    private readonly m_text: string
    private onClickSignal: IEvent<void> = new Event<void>()

    constructor(text: string, cssClass: string) {
        this.m_text = text
        this.buttonHTML.classList.add(cssClass)
    }

    getOnClickSignal() {
        return this.onClickSignal
    }

    render(parentElement: HTMLElement) {
        this.buttonHTML.innerHTML = this.m_text
        this.buttonHTML.onclick = () => this.onClickSignal.dispatch()
        parentElement.appendChild(this.buttonHTML)
    }
}

export {
    ButtonView
}