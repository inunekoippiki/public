#if( _DEBUG  )
#include <sys/stat.h>
#include "../Library/CONVERT.h"
#include "../Library/CONVERT_MA.h"
#include "../Library/createImage.h"
#include "../Library/fileUtil.h"
#include "../Library/FILE_BUFFER.h"
#include "listsFile.h"
#endif

//空のアニメーションノードに初期値をセットする
#if( _DEBUG  )
void AnimSetting(const char* fileName) {
	FILE_BUFFER fb(fileName);
	FILE* fp = fopen(fileName,"w");
	int ret = 0;
	const char* buffer = fb.buffer();
	int step = 0;//0:無し 1:nが見つかった 2,3:nの後のスペース２つ　4:空のアニメーションノード発見 
	for (int i = 0;i<fb.size();i++) {
		if (buffer[i] == 'n'&&step==0) {
			if (buffer[i - 1] == ' ' && buffer[i + 1] == ' ') {
				step = 1;
			}
		}
		if (step==1||step ==2) {
			if (buffer[i] == ' ') {
				step++;
				if (step == 3) {
					if (buffer[i + 1] == '0') {
						step = 4;
					}
					else{
						step = 0;
					}
				}
			}
		}
		if (step == 4 &&buffer[i] == '\n') {
			FILE* animDefault = fopen("Graphics/animDefault.txt", "r");
			char c;
			while ((ret = fscanf(animDefault, "%c", &c)) != EOF) {
				fprintf(fp, "%c", c);
			}
			fclose(animDefault);
			step = 0;
		}
		if (buffer[i] == '\n') {
			continue;
		}
		if (step == 4 && buffer[i] == '0') {
			fprintf(fp,"9");
		}
		else{
			fprintf(fp, "%c", buffer[i]);
		}
	}
	fclose(fp);
}
#endif

void createAssets(){
#if( _DEBUG )
    //Convert FBX to Original format
    CONVERT convert;
	CONVERT_MA convertMA;

	//convert.fbxToTree( "Graphics/floor.fbx",        "Graphics/floor.txt",   "Assets/textures/floor/" );
	//convert.fbxToTree( "Graphics/monster.fbx",      "Graphics/monster.txt", "Assets/textures/monster/" );
	//convertMA.fbxToTree("Graphics/medama.fbx", "Graphics/medama.txt", "Assets/textures/monster/");
	//convertMA.fbxToTree("Graphics/Geiza-/Medama.fbx", "Graphics/Geiza-/Medama.txt", "Assets/textures/MedamaTex/");
	//convertMA.fbxToTree("Graphics/Noa/Noa_model.fbx", "Graphics/Noa/Noa1.txt", "Assets/textures/noaTex/");
	//convertMA.fbxToTree("Graphics/Hana/Hana_Idel.fbx", "Graphics/Hana/Hana.txt", "Assets/textures/hanaTex/");
	//convertMA.fbxToTree("Graphics/minotaurosu/Boss_Idel.fbx", "Graphics/minotaurosu/Boss.txt", "Assets/textures/minotaurosuTex/");
	//convertMA.fbxToTree("Graphics/sword/sword.fbx", "Graphics/sword/sword.txt", "Assets/textures/swordTex/");
	//convertMA.fbxToTree("Graphics/stage/stage00.fbx", "Graphics/stage/stage00.txt", "Assets/textures/stage/stage00/");
	//convertMA.fbxToTree("Graphics/stage/stage01.fbx", "Graphics/stage/stage01.txt", "Assets/textures/stage/stage01/");
	//convertMA.fbxToTree("Graphics/stage/stage02.fbx", "Graphics/stage/stage02.txt", "Assets/textures/stage/stage02/");


	//convertMA.fbxToAnim( "Graphics/monster_walk.fbx", "Graphics/monster_walk.txt" );
	//convertMA.fbxToAnim("Graphics/Noa/Noa_tuuzyou.fbx", "Graphics/Noa/Noa_tuuzyou.txt" );
	//convertMA.fbxToAnim("Graphics/Noa/Noa_hasiru.fbx", "Graphics/Noa/Noa_hasiru.txt");
	//convertMA.fbxToAnim("Graphics/Noa/Noa_kinnsetukougeki.fbx", "Graphics/Noa/Noa_kinnsetukougeki.txt");
	//convertMA.fbxToAnim("Graphics/Noa/Noa_syageki.fbx", "Graphics/Noa/Noa_syageki.txt");
	//convertMA.fbxToAnim("Graphics/Noa/Noa_skill.fbx", "Graphics/Noa/Noa_skill.txt");
	//convertMA.fbxToAnim("Graphics/Noa/Noa_kaihi.fbx", "Graphics/Noa/Noa_kaihi.txt");
	//convertMA.fbxToAnim("Graphics/Noa/Noa_down.fbx", "Graphics/Noa/Noa_down.txt");
	//convertMA.fbxToAnim("Graphics/Geiza-/Medama_Idel.fbx", "Graphics/Geiza-/Medama_Idel.txt");
	//convertMA.fbxToAnim("Graphics/Geiza-/Medama_kougeki.fbx", "Graphics/Geiza-/Medama_kougeki.txt");
	//convertMA.fbxToAnim("Graphics/Geiza-/Medama_down.fbx", "Graphics/Geiza-/Medama_down.txt");
	//convertMA.fbxToAnim("Graphics/Hana/Hana_Idel.fbx", "Graphics/Hana/Hana_Idel.txt");
	//convertMA.fbxToAnim("Graphics/Hana/Hana_kougeki.fbx", "Graphics/Hana/Hana_kougeki.txt");
	//convertMA.fbxToAnim("Graphics/Hana/Hana_zyannpuidou.fbx", "Graphics/Hana/Hana_zyannpuidou.txt");
	//convertMA.fbxToAnim("Graphics/Hana/Hana_down.fbx", "Graphics/Hana/Hana_down.txt");
	//convertMA.fbxToAnim("Graphics/minotaurosu/Boss_Idel.fbx", "Graphics/minotaurosu/Boss_Idel.txt");
	//convertMA.fbxToAnim("Graphics/minotaurosu/Boss_hasiru.fbx", "Graphics/minotaurosu/Boss_hasiru.txt");
	//convertMA.fbxToAnim("Graphics/minotaurosu/Boss_kougeki.fbx", "Graphics/minotaurosu/Boss_kougeki.txt");
	//convertMA.fbxToAnim("Graphics/minotaurosu/Boss_kougeki2.fbx", "Graphics/minotaurosu/Boss_kougeki2.txt");
	//convertMA.fbxToAnim("Graphics/minotaurosu/Boss_down.fbx", "Graphics/minotaurosu/Boss_down.txt");

	//listsFile
	listsFile('x', "Assets/images/Icon", "Assets/images/Icon.txt");
	listsFile('x', "Assets/images/story", "Assets/images/story.txt");
	listsFile('x', "Assets/images/HitEffect", "Assets/images/HitEffect.txt");
	listsFile('x', "Assets/images/EnemySpawnEffect", "Assets/images/EnemySpawnEffect.txt");
	listsFile('x', "Assets/images/Debug", "Assets/images/Debug.txt");
	listsFile('x', "Assets/images/Boss_effect", "Assets/images/Boss_effect.txt");
	listsFile('x', "Assets/images/Hana_effect", "Assets/images/Hana_effect.txt");
	listsFile('x', "Assets/images/Noa_effect", "Assets/images/Noa_effect.txt");
	listsFile('x', "Assets/images/Me_effect", "Assets/images/Me_effect.txt");
	listsFile('x', "Assets/images/moero", "Assets/images/moero.txt");
	listsFile('s', "Assets/sounds/SE", "Assets/sounds/SE.txt");
	listsFile('s', "Assets/sounds/BGM", "Assets/sounds/BGM.txt");
    //Concatenate files to Assets.txt
    const char* assetsFileName = "Assets/Assets.txt";
    delFile( assetsFileName );
    addFile( assetsFileName, "Graphics/floor.txt" );
    addFile( assetsFileName, "Graphics/monster.txt" );
	addFile( assetsFileName, "Graphics/monster_walk.txt");
	addFile( assetsFileName, "Graphics/medama.txt");
	//ゲイザー
	addFile( assetsFileName, "Graphics/Geiza-/Medama.txt");
	addFile( assetsFileName, "Graphics/Geiza-/Medama_Idel.txt");
	addFile( assetsFileName, "Graphics/Geiza-/Medama_kougeki.txt");
	addFile( assetsFileName, "Graphics/Geiza-/Medama_down.txt");

	//ノア
	addFile( assetsFileName, "Graphics/Noa/Noa1.txt");
	addFile( assetsFileName, "Graphics/Noa/Noa_tuuzyou.txt");
	addFile( assetsFileName, "Graphics/Noa/Noa_hasiru.txt");
	addFile( assetsFileName, "Graphics/Noa/Noa_kinnsetukougeki.txt");
	addFile( assetsFileName, "Graphics/Noa/Noa_syageki.txt");
	addFile( assetsFileName, "Graphics/Noa/Noa_skill.txt");
	addFile( assetsFileName, "Graphics/Noa/Noa_kaihi.txt");
	addFile( assetsFileName, "Graphics/Noa/Noa_down.txt");
	//ソード
	addFile( assetsFileName, "Graphics/sword/sword.txt");
	//鼻
	addFile( assetsFileName, "Graphics/Hana/Hana.txt");
	addFile( assetsFileName, "Graphics/Hana/Hana_Idel.txt");
	addFile( assetsFileName, "Graphics/Hana/Hana_kougeki.txt");
	addFile( assetsFileName, "Graphics/Hana/Hana_zyannpuidou.txt");
	addFile( assetsFileName, "Graphics/Hana/Hana_down.txt");

	//ミノ
	addFile( assetsFileName, "Graphics/minotaurosu/Boss.txt");
	addFile( assetsFileName, "Graphics/minotaurosu/Boss_Idel.txt");
	addFile( assetsFileName, "Graphics/minotaurosu/Boss_hasiru.txt");
	addFile( assetsFileName, "Graphics/minotaurosu/Boss_kougeki.txt");
	addFile( assetsFileName, "Graphics/minotaurosu/Boss_kougeki2.txt");
	addFile( assetsFileName, "Graphics/minotaurosu/Boss_down.txt");
	//ステージ
	addFile( assetsFileName, "Graphics/stage/stage00.txt");
	addFile( assetsFileName, "Graphics/stage/stage01.txt");
	addFile( assetsFileName, "Graphics/stage/stage02.txt");

	//画像
	addFile( assetsFileName, "Assets/images/images.txt");
	addFile( assetsFileName, "Assets/images/Icon.txt");
	addFile(assetsFileName, "Assets/images/story.txt");
	addFile(assetsFileName, "Assets/images/HitEffect.txt");
	addFile(assetsFileName, "Assets/images/EnemySpawnEffect.txt");
	addFile(assetsFileName, "Assets/images/Debug.txt");
	addFile(assetsFileName, "Assets/images/Boss_effect.txt");
	addFile(assetsFileName, "Assets/images/Hana_effect.txt");
	addFile(assetsFileName, "Assets/images/Noa_effect.txt");
	addFile(assetsFileName, "Assets/images/Me_effect.txt");
	addFile(assetsFileName, "Assets/images/moero.txt");
	//音
	addFile( assetsFileName, "Assets/sounds/SE.txt");
	addFile( assetsFileName, "Assets/sounds/BGM.txt");

	//DATA
	addFile( assetsFileName, "Assets/data/data.txt" );

#endif
}
