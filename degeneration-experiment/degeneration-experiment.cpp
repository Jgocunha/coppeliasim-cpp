#include "degeneration-experiment.h"


int main()
{
    const int experimentTrials = 50;
    DegenerationExperiment experiment{experimentTrials};

    Sleep(2000);

    if (experiment.initialize())
    {
        experiment.run();
        experiment.stop();
    }

    return 0;
}
