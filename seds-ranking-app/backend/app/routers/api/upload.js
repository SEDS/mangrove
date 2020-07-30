const { Router } = require ('@onehilltech/blueprint');
const cors = require('cors');

module.exports = Router.extend ({
  specification: {
    '/uploads': {
      '/:weakness': {
        use: cors (),
        post: { action: 'upload@uploadImage' }
      }
    }
  }
});