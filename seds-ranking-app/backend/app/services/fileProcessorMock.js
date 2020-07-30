const { Service } = require ('@onehilltech/blueprint');
const { determineSCATool } = require('../utils/util')
const builder = require('xmlbuilder');
const fs = require('fs');

/**
 * @class fileProcessorMock
 */
module.exports = Service.extend({
  
  async processFile(file, weakness, tool) {
    let scaTool = determineSCATool(weakness, tool);

    var doc = builder.create('result');
    doc.att('source', `${scaTool}`)
      .att('args', '')
      .ele('weakness')
        .att('id', `CWE${weakness}`)
        .ele('source')
          .att('file', `${file.originalname}`)
          .up()
        .up()
      .ele('rankedWarnings')
        .ele('warning')
          .txt('You are trying to dereference a NULL pointer near line 13').up()
        .ele('warning')
          .txt('You are trying to dereference a NULL pointer near line 23').up()
        .ele('warning')
          .txt('You are trying to dereference a NULL pointer near line 45').up()

    let xmlPath = `../ranking/${scaTool}_CWE${weakness}_results.xml`

    // Write generated xml to a file in the Ranking python repository in
    // order to simulate the python program actually generating the 
    // correct results.
    fs.writeFileSync(xmlPath, doc.toString({ pretty: true }));

    return xmlPath
  }
})