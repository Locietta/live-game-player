#ifndef _VIEWMODEL_H_
#define _VIEWMODEL_H_

#include <cstdint>
#include <functional>

#include "./../model/model.h"
// VM must know the model's definition, and teacher does so
#include <any>

#include "./../common/notification/Notification.h"

class ViewModel : public Notification {
   public:
	ViewModel() = default;
	~ViewModel() = default;
	// void bind(std::shared_ptr<Model>);

	std::function<void(uint32_t)> get_Notification() noexcept;
	std::function<void(uint32_t)> get_xx_command() noexcept;
	void set_xx_ModelCmd(std::function<void(uint32_t)>&& cmd) noexcept;

	std::function<bool(size_t, size_t)> get_InitRdmCmd();
	std::function<bool(int)> get_Run_N_Time_Cmd();
	std::function<bool(size_t, size_t)> get_DrawCmd();

	shared_ptr<TwoDMat<bool>> Get2DBoolMat();
	void LinkToModel(const shared_ptr<Model>& spModel);

   private:
	// std::shared_ptr<Model> model;
	// std::shared_ptr<Command> command_1;
	// void dothis();
	int view_data = 0;
	function<void(uint32_t)> xx_ModelCmd;

	shared_ptr<Model> m_spModel;
};

#endif	// _VIEWMODEL_H_
