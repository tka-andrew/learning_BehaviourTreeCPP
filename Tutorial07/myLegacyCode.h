#ifndef MY_LEGACY_CODE_H
#define MY_LEGACY_CODE_H

namespace MyLegacyCode
{
    struct Point3D
    {
        double x, y, z;
    };

    // We want to create an ActionNode to calls method MyLegacyMoveTo::go
    class MyLegacyMoveTo
    {
    public:
        bool go(Point3D goal);
    };

}

#endif // MY_LEGACY_CODE_H