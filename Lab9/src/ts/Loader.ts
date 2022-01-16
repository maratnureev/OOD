import { SerializedCanvas } from "./Serializer"

abstract class FileManager {
    abstract uploadFile(onUploadCallback: (result: SerializedCanvas) => void): void
    abstract saveFile(content: string, fileName: string): void
}

class JsonFileManager implements FileManager {
    saveFile(content: string, fileName: string) {
        const a = document.createElement('a')
        const file = new Blob([content], {type: 'text/plain'})
        a.href = URL.createObjectURL(file)
        a.download = fileName
        a.click()
    }

    uploadFile(onUploadCallback: (result: SerializedCanvas) => void) {
        const input = document.createElement('input')
        input.setAttribute('type', 'file')
        input.click()
        input.addEventListener("change", () => {
            const reader = new FileReader()
            const selectedFile =  input.files && input.files[0]
            if (selectedFile) {
                reader.onload = () => {
                    if (typeof reader.result === 'string') {
                        try {
                            onUploadCallback(JSON.parse(reader.result))
                        } catch (e) {
                            alert('Invalid json file')
                        }
                    }
                }
                reader.readAsText(selectedFile)
            }
        })
    }
}

export {
    FileManager,
    JsonFileManager
}