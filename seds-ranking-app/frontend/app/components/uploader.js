import Component from '@glimmer/component';
import { tracked } from '@glimmer/tracking';
import { task } from 'ember-concurrency';
import { get, set, action } from '@ember/object'

export default class UploaderComponent extends Component {
  @tracked file;

  @(task(function * (file) {
    let product = this.modelFor('product');
    let photo = this.store.createRecord('photo', {
      product,
      filename: get(file, 'name'),
      filesize: get(file, 'size')
    });

    try {
      file.readAsDataURL().then(function (url) {
        if (get(photo, 'url') == null) {
          set(photo, 'url', url);
        }
      });

      let response = yield file.upload('/api/images/upload');
      set(photo, 'url', response.headers.Location);
      yield photo.save();
    } catch (e) {
      photo.rollback();
    }
  })) uploadPhoto;

  @action
  uploadImage(file) {
    get(this, 'uploadPhoto').perform(file);
  }
}
