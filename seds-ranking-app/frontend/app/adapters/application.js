import JSONAPIAdapter from '@ember-data/adapter/json-api';
// import FormDataAdapterMixin from 'ember-cli-form-data/mixins/form-data-adapter';

export default class ApplicationAdapter extends JSONAPIAdapter {
  host = 'http://localhost:5000';
  namespace = 'api';
}
