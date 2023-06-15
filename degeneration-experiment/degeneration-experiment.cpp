#include "degeneration-experiment.h"


int main()
{
    DegenerationExperiment experiment(10);

    if (experiment.start())
    {
        experiment.run();
        experiment.stop();
    }

    return 0;
}
