function calculateDE(D, e) {
    let res = [];
    e--;

    D.forEach((row, i) => {
        let newRow = [];

        row.forEach((elem, j) => {
            let newElem = D[i][e] + D[e][j];
            newRow.push(newElem);
        });

        res.push(newRow);
    });

    return res;
}

function sumMatrices(matrices) {
    let res = [];

    for (let i = 0; i < matrixSize; i++) {
        let row = [];

        for (let j = 0; j < matrixSize; j++) {
            let sum = matrices.reduce((sum, matrix) => sum + matrix[i][j], 0);
            row.push(sum);
        }

        res.push(row);
    }

    return res;
}

function printRes(xTilda) {
    let str = '( ';

    xTilda.forEach(value => str += `${value} `);

    str += ')\n';

    const meanValue = xTilda.reduce((sum, value) => sum + Number.parseFloat(value), 0) / xTilda.length;
    str += 'Mean value: ' + meanValue.toFixed(2);

    alert(str);
}

function calculateD(B) {
    let D = [];

    B.forEach(row => {
        let newRow = row.map(value => Math.log2(value));
        D.push(newRow);
    });

    return D;
}

function calculateX(bTilda) {
    let X = [];

    for (let j = 0; j < matrixSize; j++) {
        let sum = 0;

        for (let i = 0; i < matrixSize; i++) {
            sum += bTilda[i][j];
        }

        X.push(sum / matrixSize);
    }

    return X;
}

const B = [
    [1, 2, 3, 2, 1, 1.1, 2],
    [0.5, 1, 0.5, 3, 1.2, 1.3, 0.7],
    [0.33, 2, 1, 0.9, 2, 0.7, 3],
    [0.5, 0.33, 1.1, 1, 1, 1.7, 0.5],
    [1, 0.83, 0.5, 1, 1, 0.9, 1],
    [0.9, 0.77, 1.42, 0.58, 1.1, 1, 0.6],
    [0.5, 1.43, 0.33, 2, 1, 1.66, 1]
];
const S = 2;
const matrixSize = B.length;

// Calculate D matrix
const D = calculateD(B);

// Calculate De
const arrayDe = [];

for (let e = 1; e <= matrixSize; e++) {
    arrayDe.push(calculateDE(D, e));
}

// Calculate D~
let dTilda = sumMatrices(arrayDe);
dTilda = dTilda.map(row => row.map(item => item / matrixSize));

// Calculate B~
let bTilda = dTilda.map(row => row.map(item => S ** item));

// Calculate X array
let X = calculateX(bTilda);

// Calculate X tilda i.e. normalized X
let maxX = Math.max(...X);
let xTilda = X.map(item => (3 * item / maxX + 2).toFixed(2));

printRes(xTilda);
