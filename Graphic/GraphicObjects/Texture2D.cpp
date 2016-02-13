#include "Texture2D.h"

CTexture2D::CTexture2D(CString8 strTexturePath, CPoint originPoint) : COpenGLGraphicObject(), m_strTexturePath(strTexturePath)
{
}

void CTexture2D::DrawSelf()
{
	__super::DrawSelf();
}

void CTexture2D::CreateShaderProgram()
{
}

void CTexture2D::BindVBO()
{
}

void CTexture2D::BindEBO()
{
}

void CTexture2D::SetupVAOAttributes()
{
}
