
#pragma once
#include <cstdio>
#include <string>

template <class T>
class ArchivoBinario {
private:
    std::string nombreArchivo;

public:
    ArchivoBinario(const char* nombre);

    int ContarRegistros();
    int GenerarID();

    bool Agregar(T registro);

    bool Leer(int posicion, T& registro);

    bool Modificar(int posicion, const T& registro);

    bool BorradoLogico(int id);

    bool BuscarPorID(int id, T& registro);

    int BuscarPosicionPorID(int id);
};

template <class T>
ArchivoBinario<T>::ArchivoBinario(const char* nombre)
{
    nombreArchivo = nombre ? nombre : "";
}

template <class T>
int ArchivoBinario<T>::ContarRegistros()
{
    FILE* pFile = std::fopen(nombreArchivo.c_str(), "rb");

    if (pFile == nullptr)
    {
        return 0;
    }

    if (std::fseek(pFile, 0, SEEK_END) != 0)
    {
        std::fclose(pFile);
        return 0;
    }

    long bytes = std::ftell(pFile);
    std::fclose(pFile);

    if (bytes < 0)
    {
        return 0;
    }

    return static_cast<int>(bytes / sizeof(T));
}

template <class T>
int ArchivoBinario<T>::GenerarID()
{
    return ContarRegistros() + 1;
}

template <class T>
bool ArchivoBinario<T>::Agregar(T registro)
{
    FILE* pFile = std::fopen(nombreArchivo.c_str(), "ab");

    if (pFile == nullptr)
    {
        return false;
    }

    registro.id = GenerarID();
    registro.eliminado = false;

    bool ok = std::fwrite(&registro, sizeof(T), 1, pFile) == 1;

    std::fclose(pFile);
    return ok;
}

template <class T>
bool ArchivoBinario<T>::Leer(int posicion, T& registro)
{
    if (posicion < 0)
    {
        return false;
    }

    FILE* pFile = std::fopen(nombreArchivo.c_str(), "rb");

    if (pFile == nullptr)
    {
        return false;
    }

    if (std::fseek(pFile, posicion * static_cast<int>(sizeof(T)), SEEK_SET) != 0)
    {
        std::fclose(pFile);
        return false;
    }

    bool ok = std::fread(&registro, sizeof(T), 1, pFile) == 1;

    std::fclose(pFile);
    return ok;
}

template <class T>
bool ArchivoBinario<T>::Modificar(int posicion, const T& registro)
{
    if (posicion < 0)
    {
        return false;
    }

    FILE* pFile = std::fopen(nombreArchivo.c_str(), "rb+");

    if (pFile == nullptr)
    {
        return false;
    }

    if (std::fseek(pFile, posicion * static_cast<int>(sizeof(T)), SEEK_SET) != 0)
    {
        std::fclose(pFile);
        return false;
    }

    bool ok = std::fwrite(&registro, sizeof(T), 1, pFile) == 1;

    std::fclose(pFile);
    return ok;
}

template <class T>
int ArchivoBinario<T>::BuscarPosicionPorID(int id)
{
    FILE* pFile = std::fopen(nombreArchivo.c_str(), "rb");

    if (pFile == nullptr)
    {
        return -1;
    }

    T registro;
    int pos = 0;

    while (std::fread(&registro, sizeof(T), 1, pFile) == 1)
    {
        if (registro.id == id && !registro.eliminado)
        {
            std::fclose(pFile);
            return pos;
        }

        pos++;
    }

    std::fclose(pFile);
    return -1;
}

template <class T>
bool ArchivoBinario<T>::BuscarPorID(int id, T& registro)
{
    FILE* pFile = std::fopen(nombreArchivo.c_str(), "rb");

    if (pFile == nullptr)
    {
        return false;
    }

    while (std::fread(&registro, sizeof(T), 1, pFile) == 1)
    {
        if (registro.id == id && !registro.eliminado)
        {
            std::fclose(pFile);
            return true;
        }
    }

    std::fclose(pFile);
    return false;
}

template <class T>
bool ArchivoBinario<T>::BorradoLogico(int id)
{
    FILE* pFile = std::fopen(nombreArchivo.c_str(), "rb+");

    if (pFile == nullptr)
    {
        return false;
    }

    T registro;

    while (std::fread(&registro, sizeof(T), 1, pFile) == 1)
    {
        if (registro.id == id && !registro.eliminado)
        {
            registro.eliminado = true;

            if (std::fseek(pFile, -static_cast<long>(sizeof(T)), SEEK_CUR) != 0)
            {
                std::fclose(pFile);
                return false;
            }

            bool ok = std::fwrite(&registro, sizeof(T), 1, pFile) == 1;
            std::fclose(pFile);
            return ok;
        }
    }

    std::fclose(pFile);
    return false;
}
