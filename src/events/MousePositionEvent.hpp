#ifndef VOXELS_MOUSEPOSITIONEVENT_HPP
#define VOXELS_MOUSEPOSITIONEVENT_HPP

struct MousePositionEvent
{
    double m_xpos;
    double m_ypos;

    MousePositionEvent(double xpos, double ypos)
    : m_xpos(xpos)
    , m_ypos(ypos)
    {
    }
};

#endif //VOXELS_MOUSEPOSITIONEVENT_HPP
