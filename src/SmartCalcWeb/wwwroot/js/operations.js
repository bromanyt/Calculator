function addToExpression(ch) {
    let element = document.getElementById('expressionTextArea');
    element.textContent += ch;
}

function cleanExpression() {
    let element = document.getElementById('expressionTextArea');
    element.textContent = '';
}

function equal() {
    let element = document.getElementById('expressionTextArea');
    let x = document.getElementById('xValue').value;
    element.textContent = element.textContent.replace('x', x);
}
