CREATE TABLE
  computers (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    cpu_type VARCHAR(50) NOT NULL,
    cpu_frequency NUMERIC(5, 2) NOT NULL,
    ram_gb INT NOT NULL,
    hdd_gb INT NOT NULL,
    video_card VARCHAR(50),
    sound_card VARCHAR(50)
  );