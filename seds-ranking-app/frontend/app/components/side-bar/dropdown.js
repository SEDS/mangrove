import Component from '@glimmer/component';
import { action } from "@ember/object";
import { tracked } from '@glimmer/tracking';

export default class SideBarDropdownComponent extends Component {
  @tracked open = false;

  @action
  toggleOpenClose() {
    this.open = !this.open;
  }

  get title() {
    return this.args.title;
  }

  get contentTitle() {
    return this.args.contentTitle;
  }

  get content() {
    return this.args.content;
  }
}
