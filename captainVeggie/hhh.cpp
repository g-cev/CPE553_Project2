/*
 * @brief Moves all rabbits on the game field.This method iterates through each rabbit in the game and attempts to move it
 * to a new, adjacent position on the game field. The new position is determined
 * by adding a random delta (dx, dy) to the rabbit's current position.
 * 
 * @details
 * The deltas dx and dy are randomly generated values that can be -1, 0, or 1, 
 * which correspond to moving left/right, up/down, or staying in the same place.
 * The method ensures that rabbits only move within the bounds of the game field
 * and do not overlap with other rabbits. If the new position is occupied by a 
 * vegetable, the rabbit can still move there (as rabbits can eat vegetables).
 * 
 * @note The function checks for null pointers before attempting to move a rabbit.
 *       This is important for preventing segmentation faults in case of uninitialized
 *       or deleted rabbit objects.
 */
void GameEngine::moveRabbits()
{
    for (auto rabbit : rabbits)
    {
        if (!rabbit) continue;  // Skip if the rabbit pointer is null

        int dx = rand() % 3 - 1;  // Generates -1, 0, or 1 for the x-axis
        int dy = rand() % 3 - 1;  // Generates -1, 0, or 1 for the y-axis

        int newX = rabbit->getXPos() + dx;  // Calculate new x-coordinate
        int newY = rabbit->getYPos() + dy;  // Calculate new y-coordinate

        // Check if new coordinates are within the game field bounds
        if (newX >= 0 && newX < width && newY >= 0 && newY < height)
        {
            FieldInhabitant* occupant = field[newY][newX];

            // Cast occupant to Veggie* to check if it's a vegetable
            Veggie* veggie = dynamic_cast<Veggie*>(occupant);

            // Move the rabbit if the new position is empty or has a vegetable
            if (occupant == nullptr || veggie != nullptr)
            {
                field[rabbit->getYPos()][rabbit->getXPos()] = nullptr;  // Clear old position
                rabbit->setXPos(newX);  // Set new x-coordinate for the rabbit
                rabbit->setYPos(newY);  // Set new y-coordinate for the rabbit
                field[newY][newX] = rabbit;  // Place rabbit in the new position
            }
        }
    }
}
