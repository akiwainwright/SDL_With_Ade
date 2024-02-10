#include "VehicleState.h"


PursuitState* PursuitState::m_Instance = nullptr;

PursuitState* PursuitState::GetInstance()
{

        if (!m_Instance)
        {
            m_Instance = new PursuitState();
        }

        return m_Instance;
}

void PursuitState::Enter(VehicleAgent* _agent)
{
}

void PursuitState::Execute(VehicleAgent* _agent)
{
}

void PursuitState::Exit(VehicleAgent* _agent)
{
}

bool PursuitState::OnMessage(VehicleAgent* _agent, const Telegram&)
{
	return false;
}
