module.exports = {
  protocols : {
    http : {
      port: 5000
    }
  },

  middleware : {
    validator  : { },
    bodyParser : {
      urlencoded : { 
        extended: true
      },
      json : { },
    },

    morgan: {
      format: 'dev',
      immediate: true
    }
  }
};
