#include "stdafx.h" // Precompiled header to improve compilation time
#include "SceneManager.h"  // Include the header file for the SceneManager class
#include <cassert>    // For runtime assertions (though unused here, potentially useful)

SceneManager::~SceneManager()
{
	// Iterate through all stored states in the manager
	for (const auto& [id, state] : m_States)
	{
		// If the state pointer is not null, clean up its resources
		if(state != nullptr)
		{
			state->OnDestroy(); // Call the OnDestroy lifecycle method to free resources
		}
	}
}

void SceneManager::Update(float deltaTime)
{
	// Update the global cursor (if used for input or UI)
	Cursor::Get().Update();

	// Forward the update call to the current active scene
	if (m_Current != nullptr)
	{
		m_Current->Update(deltaTime);
	}
}
void SceneManager::Draw(sf::RenderWindow& window)
{
	// Forward the draw call to the current scene
	if (m_Current != nullptr)
	{
		m_Current->Draw();
	}
}
void SceneManager::HandleInput(float deltaTime)
{
	// Let the current scene handle input logic
	if (m_Current != nullptr)
	{
		m_Current->HandleInput(deltaTime);
	}
}
void SceneManager::Add(std::shared_ptr<IGameScene> pushingState, SceneID allocationID)
{
	// Check if the ID already exists to prevent accidental overwrite
	if (m_States.find(allocationID) != m_States.end()) 
	{
		Log::Print("State with this allocation ID already exists!", LogLevel::ERROR_);
		return; 
	}

	// Make sure the provided state is not null
	if (!pushingState) 
	{
		Log::Print("Cannot add a null state!", LogLevel::ERROR_);
		return; // Exit if the state is null
	}

	// Add the new scene to the map of states
	auto [it, hadSuccess] = m_States.emplace(allocationID, pushingState);
	if (hadSuccess)
	{
		pushingState->OnInit(); // Initialize the state once it's added successfully
	}
}

void SceneManager::Switch(SceneID stateID)
{ 
	// Look for the scene with the given ID
	auto it = m_States.find(stateID);
	auto& [id, state] = *it;

	// If a current state exists, stop it before switching
	if (it != m_States.end())
	{
		if (m_Current != nullptr)
		{
			Log::Print("Changing current state to", stateID);
			m_Current->OnStop(); // Optional pause/cleanup for switching scenes
		}

		m_Current = state; // Set new current state
		m_Current->OnStart(); // Start the newly switched state
	}
}

void SceneManager::Remove(SceneID stateID)
{
	// Locate the state
	auto it = m_States.find(stateID);
	auto& [id, state] = *it;

	if (it != m_States.end())
	{
		// If the scene being removed is the current one, unset it
		if (m_Current != nullptr)
		{
			m_Current = nullptr;
		}
		// Properly destroy the scene
		state->OnDestroy();

		// Remove the scene from the map
		m_States.erase(stateID);
	}
}

void SceneManager::Validate(SceneID ID)
{
	auto checkID = m_States.find(ID);
	// TODO: Possibly meant to confirm existence or perform some action
}
