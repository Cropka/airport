#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <vector>
#include "resource.h"
#include "agent.h"

class event : public QObject
{
private:
    Q_OBJECT
public:
    explicit event(int _timeOfOccuring, std::vector<agent>* _agents, std::vector<resource>* _subeventsResources,
                   std::vector<int> _subeventsLengths, std::vector<int> _subeventsDeadlines, std::vector<int> _subeventsPriorities,
                   QObject *parent = nullptr);
    int timeOfOccuring;
    std::vector<resource>& subeventsResources; //resources needed for each of the subevents
    std::vector<int> subeventsPriorities; //range <1,10>. 1 is highest, 10 lowest.
    std::vector<int> subeventsLengths; //length in time for each of the subevents
    std::vector<int> subeventsDeadlines;
    std::vector<agent>& agents; //event may initialise some agents, that need to be displayed on a GUI
signals:

public slots:
};

#endif // EVENT_H
