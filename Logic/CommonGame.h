#pragma once

class ICommonGame
{
public:
	virtual ~ICommonGame() {}

	virtual void Init() = 0;
	virtual void Start() = 0;
};

class CCommonGame : public ICommonGame
{
public:
	CCommonGame();

	virtual void Init() override;
	virtual void Start() override;
};
