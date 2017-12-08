#include "../include/Rocket.h"

Rocket::Rocket(DNA<Vec3> dna) : Citizen<Vec3>(dna){
    this->pos = Vec3(0,0,0);
}

Rocket::~Rocket() {

}

// void Rocket::update(Vec3 target, unsigned int current_dna) {
//     cout << "update rocket" << endl;
//     Vec3 current_gene = dna.gene_get().at(current_dna);
//     // TODO: add more checks.
//
//     // check if we have reached the target.
//     if (!failed && !reached) {
//         if (pos.get_distance(target) < 5) {
//             // we're there!
//             cout << "Rocket reached target at pos " << pos << endl;
//             reached = true;
//         } else {
//             // apply current_gene to our pos.
//             pos = pos + current_gene;
//         }
//     }
// }

float Rocket::fitness_calculate(Vec3 target) {
    float distance = pos.get_distance(target);
    // cout << "Current pos " << pos << endl;
    // cout << "Target " << target << endl;
    // cout << "Distance in rocket to t is " << distance << endl;
    fitness = 0.8f * (1.0f / (distance+1)) + 0.2f * (1.0f / (steps_taken+1));
    return fitness;
}

void Rocket::run(Vec3 target, unsigned int current_dna) {
    // move according to the Vec3's in DNA.
    vector<Vec3> genes = dna.gene_get();
    // cout << "Startpos is " << pos << endl;
    // cout << "[---------------]" << endl;
    // cout << "Adding " << genes.at(i) << " to current " << pos << endl;
    if (!reached && !failed) {
        // cout << "Adding pos" << endl;
        pos = pos + genes.at(current_dna);
        steps_taken = current_dna;
        if (pos.get_distance(target) < 5) { // if withing 5 pixels.
            reached = true;
            // cout << "Rocket reached target pos at " << pos << " in " << steps_taken << " steps" << endl;
        }
        // TODO: add checks for failed.
    } else {
        // rocket has either reached target or failed in doing so.
    }
    // cout << "Ended up at " << pos << endl;
    // cout << "----" << endl;
    // cout << "Final pos --------" << pos << endl;
}


ostream& operator<< (ostream & out, const Rocket &data) {
    out << "Rocket " << data.pos << " steps " << data.steps_taken << flush;
    return out;
}
