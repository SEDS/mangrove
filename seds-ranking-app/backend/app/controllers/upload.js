const {
  Controller,
  Action,
  service,
  SingleFileUploadAction
} = require ('@onehilltech/blueprint');
const USE_MOCK = true;
const fs = require('fs');
var xml2js = require('xml2js');

/**
 * @class upload
 */
module.exports = Controller.extend ({
  fpService: (USE_MOCK) ? service('fileProcessorMock') : service('fileProcessor'),

  uploadImage () {
    return SingleFileUploadAction.extend ({
      uploadPath: './temp',
      name: 'file',
      
      async onUploadComplete (req, res) {

        let weakness = req.params.weakness.split(':')[0];
        weakness = Number.parseInt(weakness);
        let tool = req.params.weakness.split(':')[1];

        // process the file
        let xmlPath = await this.controller.fpService.processFile(req.file, weakness, tool);

        // get results after processing
        let results = await this.parseResults(xmlPath, weakness);

        // send result to requester
        this.sendResponse(res, results);
      },

      sendResponse(res, results) {
        res.status(200).json({
          data: results
        });
      },

      async parseResults(xmlPath, weakness) {
        let fileContent = fs.readFileSync(xmlPath, 'utf8');
        
        let data = await xml2js.parseStringPromise(fileContent)
        let warnings = data.result.rankedWarnings[0].warning

        let results = {
          id: `CWE-${weakness}`,
          type: `warnings`,
          attributes: {
            messages: warnings
          }
        };

        return results
      }
    });
  },
});
