# 📖 GUÍA COMPLETA DE GIT WORKFLOW PARA MINISHELL

## 🎯 RESUMEN EJECUTIVO

**Estrategia de trabajo en equipo:**
- **Cada desarrollador** trabaja en su **propia rama**
- **Sincronización regular** con la rama principal (`main`)
- **Integración final** mediante Pull Requests
- **Comunicación constante** entre compañeros

---

## 🚩 FLAGS DE GIT - REFERENCIA RÁPIDA

### 📋 `git branch`:
```bash
git branch          # Ver ramas locales
git branch -a       # -a = ALL (locales + remotas)
git branch -r       # -r = REMOTE (solo remotas)
git branch -d rama  # -d = DELETE (borrar rama)
git branch -D rama  # -D = DELETE FORCE (forzar borrado)
```

### 📋 `git checkout`:
```bash
git checkout rama       # Cambiar a rama existente
git checkout -b nueva   # -b = BRANCH (crear nueva + cambiar)
git checkout -B nueva   # -B = BRANCH FORCE (recrear si existe)
```

### 📋 `git push`:
```bash
git push origin rama    # Subir rama al servidor
git push -u origin rama # -u = UPSTREAM (establecer tracking)
git push -f origin rama # -f = FORCE (forzar push - PELIGROSO)
git push               # Solo funciona con tracking establecido
```

### 📋 `git pull/merge`:
```bash
git pull origin main   # Traer cambios de main remoto
git merge main         # Fusionar main en rama actual
git fetch origin       # Actualizar referencias sin fusionar
```

---

## 📋 CHECKLIST DIARIO

### 🔲 Al empezar:
- [ ] `git checkout main`        # Ir a main primero
- [ ] `git pull origin main`     # Actualizar main local
- [ ] `git checkout tu_rama`     # Ir a tu rama
- [ ] `git merge main`           # Traer cambios limpios

### 🔲 Durante trabajo:
- [ ] Commits frecuentes
- [ ] `git push` regularmente
- [ ] Probar que compila

### 🔲 Al terminar:
- [ ] `git add .`
- [ ] `git commit -m "mensaje"`
- [ ] `git push`

---

## ⚙️ CONFIGURACIÓN INICIAL (SOLO UNA VEZ)

### 🔧 Paso a paso:

```bash
# 1. Asegurarse de estar en main actualizado
git checkout main
git pull origin main

# 2. Crear ramas desde main actualizado
# DESARROLLADOR 1 (señales):
git checkout -b signals
git push -u origin signals

# DESARROLLADOR 2 (lexer):
git checkout -b lexer  
git push -u origin lexer

# 3. Verificar que aparecen las ramas
git branch -a
```

### 📊 Resultado esperado:
```bash
* signals  (o lexer, según quién lo ejecute)
  main
  remotes/origin/HEAD -> origin/main
  remotes/origin/lexer
  remotes/origin/main  
  remotes/origin/signals
```

---

### 💻 DURANTE EL TRABAJO:
```bash
# Cada funcionalidad pequeña completada:
git add .
git commit -m "feat: implement SIGINT handler"
git push                    # (funciona gracias al -u inicial)

# Cada 2-3 commits (sincronización):
git pull origin main
git merge main
```

### 🌙 AL FINAL DEL DÍA:
```bash
git add .
git commit -m "wip: working on signal cleanup"
git push
```

---

## 🔄 COMANDOS DE SINCRONIZACIÓN

### 📥 Traer cambios del compañero:
```bash
git fetch origin              # Actualizar todas las referencias
git checkout lexer            # Ver rama del compañero (solo lectura)
git checkout signals          # Volver a tu rama
```

### 🔄 Manejo de conflictos:
```bash
git pull origin main
git merge main
# Si hay conflictos:
# 1. Resolver conflictos en editor
# 2. git add archivos_resueltos
# 3. git commit -m "merge: resolve conflicts with main"
# 4. git push
```

---

## 🧪 COMANDOS DE DEBUGGING/INFORMACIÓN

### 🔍 Ver estado y diferencias:
```bash
git status                    # Estado actual de archivos
git diff                      # Cambios no committeados
git diff main                 # Comparar tu rama con main
git log --oneline --graph     # Historial gráfico
git branch -a                 # Todas las ramas
```

### 📊 Comparaciones entre ramas:
```bash
git diff main signals                    # Diferencias generales
git diff main signals -- srcs/main.c    # Archivo específico
git log main..signals --oneline         # Commits únicos de tu rama
```

---

## 🔗 INTEGRACIÓN FINAL

### 📝 Cuando termines tu parte:
```bash
# 1. Preparar rama para fusión
git checkout signals
git pull origin main
git merge main                # Resolver conflictos si los hay
git push

# 2. Crear Pull Request en GitHub:
#    "Merge signals into main"

# 3. Code review del compañero

# 4. Fusionar a main

# 5. Limpiar (después de fusionar):
git checkout main
git pull origin main
git branch -d signals         # Borrar rama local
```

---

## 💡 MEJORES PRÁCTICAS

### ✅ Commits:
- **Frecuentes y pequeños** (cada funcionalidad)
- **Mensajes descriptivos**: `feat:`, `fix:`, `refactor:`, `wip:`
- **Un commit = una funcionalidad**

### ✅ Sincronización:
- **Pull de main** al menos 2 veces al día
- **Resolver conflictos** inmediatamente
- **Comunicar cambios importantes** al compañero

### ✅ Comunicación:
- **Avisar** antes de modificar archivos compartidos
- **Documentar** interfaces entre módulos  
- **Reuniones breves** para sincronizar progreso

### ✅ Testing:
- **Probar tu rama** antes de hacer push
- **Testing conjunto** después de cada merge a main
- **No romper** la compilación en main

---

## 🚨 COMANDOS DE EMERGENCIA

### ⚠️ Si algo sale mal:
```bash
# Deshacer último commit (local):
git reset --soft HEAD~1

# Volver a estado anterior:
git checkout -- archivo.c    # Descartar cambios de archivo
git stash                    # Guardar cambios temporalmente
git stash pop                # Recuperar cambios guardados

# Forzar sincronización (CUIDADO):
git reset --hard origin/main  # Volver exactamente a main remoto
```

---

git fetch origin
git log HEAD..origin/main --oneline       # commits que te faltan
git log origin/main..HEAD --oneline       # commits que solo tienes tú
git rev-list --left-right --count origin/main...HEAD
git diff origin/main
git log --oneline --graph --decorate --all
