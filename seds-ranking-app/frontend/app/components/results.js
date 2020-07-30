import Component from '@glimmer/component';
import { action } from "@ember/object";

export default class ResultsComponent extends Component {
  @action
  clear() {
    this.args.parent.clear();
  }

  get hasErrors() {
    return (this.args.results.messages) ? true : false;
  }
}
