#include "Frustum.h"

#include "OctTree.h"


void Frustum::InterSect( aabbox& box )
{
	
}


bool Frustum::InterSect( point& p )
{
	std::vector<Plane> planes  = FormPlane();
	
	for (unsigned int i = 0;i<planes.size();i++)
	{
		if(planes[i].A*p.X()+planes[i].B*p.Y()+planes[i].C*p.Z()+planes[i].D > 0.f)
		{
			return false;
		}
	}
	return true;
}

std::vector<Plane> Frustum::FormPlane()
{
	std::vector<Plane> vPlane;
	vPlane.resize(6);
   
	point   fnOri  = m_NLUp;
	point   fndir1 = m_NLBp - m_NLUp;
	point   fndir2 = m_NRUp - m_NLUp;
	Plane	faceNear(fnOri,fndir1,fndir2);//近裁剪面

	point   ffOri  = m_FRBp;
	point   ffdir1 = m_FRBp - m_FRUp;
	point   ffdir2 = m_FLUp - m_FRUp;
	Plane	faceFar(ffOri,ffdir1,ffdir2);//远裁剪面

	point   frOri  = m_NRUp;
	point   frdir1 = m_NRBp - m_NRUp;
	point   frdir2 = m_FRUp - m_NRUp;
	Plane	faceRight(frOri,frdir1,frdir2);//右面

	point   flOri  = m_FLUp;
	point   fldir1 = m_FLBp - m_FLUp;
	point   fldir2 = m_NLUp - m_FLUp;
	Plane	faceLeft(flOri,fldir1,fldir2);//左面

	point   fuOri  = m_FRUp;
	point   fudir1 = m_FLBp - m_FRUp;
	point   fudir2 = m_NRUp - m_FRUp;
	Plane	faceUP(fuOri,fudir1,fudir2);//上面

	point   fbOri  = m_NRBp;
	point   fbdir1 = m_NLBp - m_NRBp;
	point   fbdir2 = m_FRBp - m_NRBp;
	Plane	faceButtom(fbOri,fbdir1,fbdir2);//下面
	
	vPlane.push_back(faceNear);
	vPlane.push_back(faceFar);
	vPlane.push_back(faceLeft);
	vPlane.push_back(faceRight);
	vPlane.push_back(faceUP);
	vPlane.push_back(faceButtom );
	return vPlane;
}
