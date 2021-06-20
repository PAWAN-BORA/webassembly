
const {exec} = require('child_process');
const fs = require('fs');

let rootDir = "./src";
let subPart = "";
// fs.readdirSync(rootDir).forEach(file => {
//     console.log(file);
//     // if()
//     if(file.match('[^.]+$')[0]=="cpp") {
//         subPart += `src/${file} `;
//     }
// });

function getAllFiles(dir) {
    fs.readdirSync(dir).forEach(file =>{
        let statObj = fs.statSync(`${dir}/${file}`);
        // console.log(statObj.isDirectory());
        if(statObj.isDirectory()) {
            getAllFiles(dir+'/'+file);
        } else {
            if(file.match('[^.]+$')[0]=="cpp") {
                subPart += `${dir}/${file} `;
            }  
        }
    })
}
getAllFiles(rootDir);
// console.log("below is subpart")
// console.log(subPart);
exec(`em++ ${subPart} -s WASM=1 -o static/main.js -s EXPORTED_RUNTIME_METHODS=[cwrap]`, callBack);


function callBack(err, stdout, stderr) {
    if(err){
        console.log(err);
        return;
    }
    if(stdout) {
        console.log(stdout);
    }
    if(stderr){
        // console.log("Waring");
        console.log(stderr);
    }
}