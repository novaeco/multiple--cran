# Instructions pour Codex



## Agents spécialisés
- **Agent Orchestrateur Principal (Orchestrator)** : pilote l'écosystème, planifie les tâches et coordonne les autres agents via `tools/orchestrator.py`.
- **Agent de Provisioning & Setup (Provisioner)** : installe et met à jour les outils de développement et vérifie la disponibilité de l'ESP‑IDF à l'aide de `tools/provisioner.py` qui exécute `setup.sh` si besoin.
- **Agents de Développement Par Langage (DevAgent[Lang])** : fournissent l'expertise pour chaque technologie et proposent de bonnes pratiques.
- **DevAgent UI/UX Full Stack** : conçoit des interfaces esthétiques, fonctionnelles et accessibles en mêlant design et développement front‑end/back‑end.
- **DevAgent LVGL Full Stack** : réalise des interfaces graphiques avancées pour l'embarqué et l'IoT tout en tenant compte des contraintes matérielles.
- **DevAgent JS/TS Full Stack** : développe des applications Web complètes avec l'écosystème JavaScript/TypeScript, du frontend au backend.
- **DevAgent Python Full Stack** : couvre le développement Web, la science des données et l'IA jusqu'au déploiement de modèles de machine learning.
- **DevAgent Go Full Stack** : crée des services cloud‑native et des microservices performants pour des architectures distribuées.
- **DevAgent Rust Full Stack** : fournit des solutions sûres et performantes pour la programmation système et le WebAssembly.
- **DevAgent Java Full Stack** : conçoit des applications d'entreprise évolutives et maintenables dans l'écosystème Java.
- **DevAgent C/C++ Full Stack** : se spécialise dans les systèmes embarqués et les logiciels hautes performances.
- **DevAgent C#/.NET Full Stack** : offre des solutions complètes pour les applications et services basés sur l'écosystème Microsoft .NET.
- **DevAgent PHP Full Stack** : propose des plateformes Web et e‑commerce complètes avec PHP et ses frameworks.
- **DevAgent Ruby Full Stack** : privilégie le développement Web rapide et maintenable avec Ruby et Rails.
- **DevAgent Assembly Full Stack** : optimise le code au plus bas niveau pour un contrôle matériel et des performances maximales.
- **Agent Build & CI (Builder)** : centralise la compilation et la CI/CD en appliquant les options de `sdkconfig.defaults`.
- **Agent de Test & Qualité (Tester)** : automatise les tests et le lint pour garantir un firmware stable.
- **Agent Déploiement & Infrastructure (Deployer)** : gère le déploiement et l'infrastructure en tenant compte des écrans cibles.
- **Agent d’Observabilité & Monitoring (Observer)** : agrège logs et métriques pour faciliter le diagnostic.
- **Agent de Documentation & Assistance (DocAgent)** : génère et maintient la documentation, y compris ce fichier.
- **Agent de Collaboration (CollabAgent)** : facilite la gestion de branches et tickets et suit l'avancement global.

## Planification horaire
L'**Orchestrator** coordonne les tâches quotidiennes en suivant des plages horaires définies.
Chaque matin, il lance `tools/provisioner.py` pour que le **Provisioner** vérifie le setup et exécute `setup.sh` si nécessaire.
Le **Builder** déclenche des compilations régulières au fil de la journée.
Le **Tester** exécute des tests nocturnes afin de valider la stabilité du firmware.
Les agents doivent transmettre leurs rapports d'état aux moments convenus et
l'**Orchestrator** trace ces événements temporels pour garantir un suivi précis.
