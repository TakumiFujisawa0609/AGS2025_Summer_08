#include <DxLib.h>
#include "../Application.h"
#include "Resource.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::instance_ = nullptr;

void ResourceManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new ResourceManager();
	}
	instance_->Init();
}

ResourceManager& ResourceManager::GetInstance(void)
{
	return *instance_;
}

void ResourceManager::Init(void)
{
	using RES = Resource;
	using RES_T = RES::TYPE;
	static std::string PATH_IMG = Application::PATH_IMAGE;
	static std::string PATH_MDL = Application::PATH_MODEL;
	static std::string PATH_EFF = Application::PATH_EFFECT;

	Resource* res;

	res = new RES(RES_T::IMG, PATH_IMG + "Title.png");
	resourcesMap_.emplace(SRC::TITLE, res);

	res = new RES(RES_T::IMG, PATH_IMG + "Button/Title/Normal_GameStart.png");
	resourcesMap_.emplace(SRC::NORMAL_GAMESTART, res);

	res = new RES(RES_T::IMG, PATH_IMG + "Button/Title/Normal_Exit.png");
	resourcesMap_.emplace(SRC::NORMAL_EXIT, res);

	res = new RES(RES_T::IMG, PATH_IMG + "Button/Title/Hover_GameStart.png");
	resourcesMap_.emplace(SRC::HOVER_GAMESTART, res);

	res = new RES(RES_T::IMG, PATH_IMG + "Button/Title/Hover_Exit.png");
	resourcesMap_.emplace(SRC::HOVER_EXIT, res);

	res = new RES(RES_T::MODEL, PATH_MDL + "Player/Player.mv1");
	resourcesMap_.emplace(SRC::PLAYER, res);

	res = new RES(RES_T::MODEL, PATH_MDL + "Player/Idle.mv1");
	resourcesMap_.emplace(SRC::IDLE, res);

	res = new RES(RES_T::MODEL, PATH_MDL + "Player/Run.mv1");
	resourcesMap_.emplace(SRC::RUN, res);

	res = new RES(RES_T::MODEL, PATH_MDL + "Player/FastRun.mv1");
	resourcesMap_.emplace(SRC::FAST_RUN, res);

	res = new RES(RES_T::MODEL, PATH_MDL + "Stage/MainStage/MainStage.mv1");
	resourcesMap_.emplace(SRC::MAIN_STAGE, res);
}

void ResourceManager::Release(void)
{
	for (auto& p : loadedMap_)
	{
		p.second.Release();
	}

	loadedMap_.clear();
}

void ResourceManager::Destroy(void)
{
	Release();
	for (auto& res : resourcesMap_)
	{
		res.second->Release();
		delete res.second;
	}
	resourcesMap_.clear();
	delete instance_;
}

const Resource& ResourceManager::Load(SRC src)
{
	const Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return dummy_;
	}
	return res;
}

int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res.handleId_);
	res.duplicateModelIds_.push_back(duId);

	return duId;
}

ResourceManager::ResourceManager(void)
{
}

Resource& ResourceManager::_Load(SRC src)
{

	// ロード済みチェック
	const auto& lPair = loadedMap_.find(src);
	if (lPair != loadedMap_.end())
	{
		return *resourcesMap_.find(src)->second;
	}

	// リソース登録チェック
	const auto& rPair = resourcesMap_.find(src);
	if (rPair == resourcesMap_.end())
	{
		// 登録されていない
		return dummy_;
	}

	// ロード処理
	rPair->second->Load();

	// 念のためコピーコンストラクタ
	loadedMap_.emplace(src, *rPair->second);

	return *rPair->second;

}
