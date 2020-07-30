import Controller from '@ember/controller';
import { action } from '@ember/object';
import { tracked } from '@glimmer/tracking';

export default class UploadController extends Controller {
  flawFinderWeaknesses = ["126", "134"];
  cppCheckWeaknesses = ["401", "476", "762" ];
  tool = ["CppCheck", "FlawFinder"];

  @tracked weaknesses;
  @tracked results = null;
  @tracked selectedTool;
  @tracked selectedWeakness;


  @action
  weaknessChanged(change) {
    this.model.weakness = change;
    this.results = null;
  }

  @action
  toolChanged(change) {
    this.model.tool = change;
    this.selectedWeakness = null;

    if (change === "CppCheck") {
      this.weaknesses = this.cppCheckWeaknesses;
    }
    else {
      this.weaknesses = this.flawFinderWeaknesses;
    }

    this.results = null;
  }

  @action
  setFile(changeset, file) {
    changeset.set('file', file);
    let self = this;
    if (changeset.file) {
      let file = changeset.file;

      // Make sure there is a weakness radio button chosen
      if (this.model.weakness) {
        file.upload(`http://localhost:5000/api/uploads/${this.selectedWeakness}:${this.selectedTool}`).then((res) => {
          self.results = res.body.data.attributes;
        });
      }
    }
  }

  @action
  clear() {
    this.results = null;
  }
}
