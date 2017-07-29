using namespace std;

int getCurrentMission(int x) {
	int mission = 0;
	if (x > 400) mission = 1;
	else if (x > 700) mission = 2;
	else if (x > 2200) mission = 3;
	return mission;
}

wstring getTextMission(int currentMission) {
	wstring missionText = L"";

	switch (currentMission) {
		case 0: missionText = L"\nНачальный этап и \nинструкции к игре"; break;
		case 1: missionText = L"\nMission 1\n\nВот твоя первая\n миссия, на\n этом уровне \nтебе стоит опасаться\n ... бла-бла-бла ..."; break;
		case 2: missionText = L"\nMission 2\n Необходимо решить\n логическую задачку,\n чтобы пройти дальше "; break;
		case 3: missionText = L"\nИ так далее \nи тому подобное....."; break;
	}

	return missionText;
}