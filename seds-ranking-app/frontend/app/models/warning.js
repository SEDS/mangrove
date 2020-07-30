import Model, { attr } from '@ember-data/model';

export default class WarningModel extends Model {
  @attr messages;
}
