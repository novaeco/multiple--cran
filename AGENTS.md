# Instructions pour Codex



## Agents spécialisés
- **Agent Orchestrateur Principal (Orchestrator)** : pilote l'écosystème, planifie les tâches et coordonne les autres agents.
- **Agent de Provisioning & Setup (Provisioner)** : installe et met à jour les outils de développement et vérifie la disponibilité de l'ESP‑IDF.
- **Agents de Développement Par Langage (DevAgent[Lang])** : fournissent l'expertise pour chaque technologie et proposent de bonnes pratiques.
- **Agent Build & CI (Builder)** : centralise la compilation et la CI/CD en appliquant les options de `sdkconfig.defaults`.
- **Agent de Test & Qualité (Tester)** : automatise les tests et le lint pour garantir un firmware stable.
- **Agent Déploiement & Infrastructure (Deployer)** : gère le déploiement et l'infrastructure en tenant compte des écrans cibles.
- **Agent d’Observabilité & Monitoring (Observer)** : agrège logs et métriques pour faciliter le diagnostic.
- **Agent de Documentation & Assistance (DocAgent)** : génère et maintient la documentation, y compris ce fichier.
- **Agent de Collaboration (CollabAgent)** : facilite la gestion de branches et tickets et suit l'avancement global.

## Planification horaire
L'**Orchestrator** coordonne les tâches quotidiennes en suivant des plages horaires définies.
Chaque matin, le **Provisioner** vérifie le setup et la disponibilité des outils.
Le **Builder** déclenche des compilations régulières au fil de la journée.
Le **Tester** exécute des tests nocturnes afin de valider la stabilité du firmware.
Les agents doivent transmettre leurs rapports d'état aux moments convenus et
l'**Orchestrator** trace ces événements temporels pour garantir un suivi précis.
