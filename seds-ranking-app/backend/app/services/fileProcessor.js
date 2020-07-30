const { Service } = require ('@onehilltech/blueprint');
const { determineSCATool } = require('../utils/util')

/**
 * @class fileProcessor
 */
module.exports = Service.extend({
  
  async processFile(file, weakness, tool) {
    let sca = determineSCATool(weakness, tool)
    await new Promise(
      (success, nosuccess) => {
        const spawn = require('child_process').spawn;
        const pyProg = spawn('python', 
          [
            `../ranking/main.py`,
            `--weakness=CWE${weakness}`,
            `--SCATool=${sca}`,
            `--sourceCode=./temp/${file.filename}`
          ]
        );
    
        pyProg.stderr.on('data', (error) => {
          console.error(error.toString('utf8'));
          nosuccess(error)
        });
    });

    return `../ranking/${sca}_CWE${weakness}_results.xml`
  },
})
