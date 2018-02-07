#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"


sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{

}


DWORD CALLBACK loadingThread(LPVOID prc)
{
	//�ٲ��� ���� �̸� �ʱ�ȭ�� �д�
	sceneManager::_readyScene->init();

	//���� ������ ��ü ���ش�
	sceneManager::_currentScene = sceneManager::_readyScene;

	//�ε��� ���� ���� �������ְ�, �����ѳ��� ���� ����
	sceneManager::_loadingScene->release();
	sceneManager::_loadingScene = NULL;
	sceneManager::_readyScene = NULL;

	//�߿��Ѱ� �Ƹ� ���� ���ٴ°� �Ǹ�������...

	return 0;
}

//����ƽ���� ���� �Ǿ������Ƿ� �ʱ�ȭ�� ���⼭
gameNode* sceneManager::_currentScene = NULL;
gameNode* sceneManager::_loadingScene = NULL;
gameNode* sceneManager::_readyScene = NULL;

HRESULT sceneManager::init(void)
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;


	return S_OK;
}

void sceneManager::release(void)
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
}

void sceneManager::update(void)	
{
	if (_currentScene) _currentScene->update();
}

void sceneManager::render(void)	
{
	if (_currentScene) _currentScene->render();
}


//�� �߰� �Լ�
gameNode* sceneManager::addScene(string sceneName, gameNode* scene)
{
	//���� ���ٸ� �ΰ� ��ȯ
	if (!scene) return NULL;

	//���� Ű ���� �ο��ؼ� map�����̳ʿ� ����ش�
	_mSceneList.insert(make_pair(sceneName, scene));

	//��ȯ
	return scene;
}

gameNode* sceneManager::addLoadingScene(string loadingSceneName, gameNode* scene)
{
	//���� ���� ���ٸ� NULL�� ��ȯ
	if (!scene) return NULL;

	//�ε����� Ű���� �ٿ��� �������̳ʿ� ����ش�
	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

//�� ����
HRESULT sceneManager::changeScene(string sceneName)
{
	//���ͷ����Ϳ� ã�����ϴ� ���� Ű ���� ����
	mapSceneIter find = _mSceneList.find(sceneName);

	//���ͷ����Ͱ� ���� ������ ���� == ã�����ϴ°� ���� ���� ��ȯ
	if (find == _mSceneList.end()) return E_FAIL;

	//���� �ٲٷ��� ���� ���� ���̸� �׳� �д�
	if (find->second == _currentScene) return S_OK;

	//���������� ���� �ٲ�ٸ� init�Լ� ���� 
	if (SUCCEEDED(find->second->init()))
	{
		//���� ������� �ٸ� ���� �ִٸ� ���� ���ְ�
		if (_currentScene) _currentScene->release();

		//�ٲٷ��� ������ ü���� �Ѵ�
		_currentScene = find->second;

		//���� �� ��ȯ�ϴ� �� ������ �������� �Ը��� ���� �ٲ㵵 �ȴ�
		//����Ʈ�� ����� ������ ���� ������ ������ �� �ϳ� �ִµ�
		//��������1 -> ��������2�� ���� �ٲ������ ��������1�� �����͸�
		//�ѱ���� �Ҷ� ����� ���� ȣ���� �Ǽ� ���� �Ű��� ������Ѵ�

		//�� �׷��ٰ�.. �� _��)

		return S_OK;
	}

	return E_FAIL;
}

HRESULT sceneManager::changeScene(string sceneName, string loadingSceneName)
{
	//���ͷ����Ϳ� ã�����ϴ� ���� Ű ���� ����
	mapSceneIter find = _mSceneList.find(sceneName);


	if (find == _mSceneList.end()) return E_FAIL;
	if (find->second == _currentScene) return S_OK;

	//�ε��Ϸ��� ���� ã�´�
	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);

	//����ó�� ����?
	if (find == _mLoadingSceneList.end()) return changeScene(loadingSceneName);

	//���������� ���� �ٲ�ٸ� init�Լ� ���� 
	if (SUCCEEDED(find->second->init()))
	{
		//���� ������� �ٸ� ���� �ִٸ� ���� ���ְ�
		if (_currentScene) _currentScene->release();

		//�ε����� ã�Ƽ� �����ϰ�
		_loadingScene = findLoading->second;
		//�ٲٷ��� ���� �غ���ѵд�
		_readyScene = find->second;
		
		//�ε��� ���� ������ ���ش�
		CloseHandle(CreateThread(NULL, 0, loadingThread, NULL, 0, &_loadingThreadID));
	
		return S_OK;
	}

	return E_FAIL;
}

