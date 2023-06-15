#include "degeneration-experiment.h"


int main()
{
    const int experimentTrials = 10;
    DegenerationExperiment experiment{experimentTrials};

    if (experiment.initialize())
    {
        experiment.run();
        experiment.stop();
    }

    return 0;
}
