class EspFunctions
{
public:
    static int GetFreeHeap()
    {
        return ESP.getFreeHeap();
    }

    static void Restart()
    {
        esp_restart();
    }
};