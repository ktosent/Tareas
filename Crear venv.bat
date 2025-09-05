::Crear Venv
@echo off 
echo creando venv
python -m venv .venv && echo venv creado
echo activando entorno virtual
call .venv\Scripts\actívate && echo entorno activado
pause
